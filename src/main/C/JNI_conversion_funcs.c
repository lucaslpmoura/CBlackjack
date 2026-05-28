#include <stdlib.h>
#include <stdbool.h>
#include <jni.h>

#include "JNI_conversion_funcs.h"

void convert_obj_to_card(JNIEnv *env, Card *card, jobject jcard){
    if(jcard == NULL) return;

    jclass cardClass = (*env)->GetObjectClass(env, jcard);

    //Suit
    jfieldID suitField = (*env)->GetFieldID(
        env,
        cardClass,
        "suit",
        "Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Suit;"
    );

    jobject jsuit = (*env)->GetObjectField(env, jcard, suitField);

    jclass suitEnumClass = (*env)->GetObjectClass(env, jsuit);

    jmethodID suitOrdinalMethod = (*env)->GetMethodID(
        env,
        suitEnumClass,
        "ordinal",
        "()I"
    );

    jint suitOrdinal = (*env)->CallIntMethod(env, jsuit, suitOrdinalMethod);
    card->suit = (Suit) suitOrdinal;

    //Value
    jfieldID valueField = (*env)->GetFieldID(
        env,
        cardClass,
        "value",
        "Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Value;"
    );

    jobject jvalue = (*env)->GetObjectField(env, jcard, valueField);

    jclass valueEnumClass = (*env)->GetObjectClass(env, jvalue);

    jmethodID valueOrdinalMethod = (*env)->GetMethodID(
         env,
         valueEnumClass,
         "ordinal",
         "()I"
    );

    jint valueOrdinal = (*env)->CallIntMethod(env, jvalue, valueOrdinalMethod);

    card->value = (Value)valueOrdinal;

    // is_hidden
    jfieldID is_hiddenField = (*env)->GetFieldID(
        env,
        cardClass,
        "is_hidden",
        "Z" // Z stands for boolean - beats me
    );

    jboolean hidden = (*env)->GetBooleanField(env, jcard, is_hiddenField);

    card->is_hidden = (bool)hidden;

    //next - let the deck conversion handle this
    card->next = NULL;
}

void convert_card_to_obj(JNIEnv *env, Card *card, jobject jcard) {

    jclass cardClass = (*env)->FindClass(
        env,
        "com/lucaslpmoura/JNI_Blackjack/CBlackjack$Card"
    );

    //Suit
    jfieldID suitField = (*env)->GetFieldID(
        env,
        cardClass,
        "suit",
        "Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Suit;"
    );
    jclass suitClass = (*env)->FindClass(
        env,
        "com/lucaslpmoura/JNI_Blackjack/CBlackjack$Suit"
    );

    jmethodID valuesMethod = (*env)->GetStaticMethodID(
       env,
       suitClass,
       "values",
       "()[Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Suit;"
    );


    jobjectArray suitValues = (jobjectArray)(*env)->CallStaticObjectMethod(env, suitClass, valuesMethod);
    jobject jsuit = (*env)->GetObjectArrayElement(env, suitValues, card->suit);
    (*env)->SetObjectField(env, jcard, suitField, jsuit);

    //Value
    jfieldID valueField = (*env)->GetFieldID(
        env,
        cardClass,
        "value",
        "Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Value;"
    );
    jclass valueClass = (*env)->FindClass(
        env,
        "com/lucaslpmoura/JNI_Blackjack/CBlackjack$Value"
    );

    valuesMethod = (*env)->GetStaticMethodID(
       env,
       valueClass,
       "values",
       "()[Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Value;"
    );

    jobjectArray valueValues = (jobjectArray)(*env)->CallStaticObjectMethod(env, valueClass, valuesMethod);
    jobject jvalue = (*env)->GetObjectArrayElement(env, valueValues, card->value);
    (*env)->SetObjectField(env, jcard, valueField, jvalue);

    //next -- deck conversion should handle this
    jfieldID nextField = (*env)->GetFieldID(
        env,
        cardClass,
        "next",
        "Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Card;"
    );
    (*env)->SetObjectField(env, jcard, nextField, NULL);

    //is_hidden
    jfieldID is_hiddenField = (*env)->GetFieldID(
        env,
        cardClass,
        "is_hidden",
        "Z" //boolean
    );
    (*env)->SetBooleanField(env, jcard, is_hiddenField, (bool)card->is_hidden);

}






// HAND FUNCTIONS
void convert_obj_to_hand(JNIEnv *env, Hand *hand, jobject jhand) {
    if(jhand == NULL) return;

    jclass handClass = (*env)->GetObjectClass(env, jhand);

    //num_of_cards
    jfieldID num_of_cardsField = (*env)->GetFieldID(
        env,
        handClass,
        "num_of_cards",
        "C"
    );

    jchar num_of_cards = (*env)->GetCharField(env, jhand, num_of_cardsField);

    hand->num_of_cards = (char)num_of_cards;

    //size
    jfieldID sizeField = (*env)->GetFieldID(
        env,
        handClass,
        "size",
        "I"
    );

    jint size = (*env)->GetIntField(env, jhand, sizeField);

    hand->size = (int)size;

    //cards
    jfieldID cardsField = (*env)->GetFieldID(
        env,
        handClass,
        "cards",
        "[Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Card;"
    );

    jobjectArray jcards = (jobjectArray) (*env)->GetObjectField(env, jhand, cardsField);
    jsize len = (*env)->GetArrayLength(env, jcards);

    hand->cards = malloc(sizeof(Card) * len);
    for(char i = 0; i < len; i++){
        jobject jcard = (*env)->GetObjectArrayElement(env, jcards, i);

        Card *card = malloc(sizeof(Card));
        convert_obj_to_card(env, card, jcard);
        hand->cards[i] = card;
    }

}








// DECK FUNTIONS
void convert_deck_to_obj(JNIEnv *env, Deck *deck, jobject jdeck){
    if(deck == NULL) return;


    jclass deckClass = (*env)->FindClass(
            env,
            "com/lucaslpmoura/JNI_Blackjack/CBlackjack$Deck"
    );

    //size
    jfieldID sizeField = (*env)->GetFieldID(
        env,
        deckClass,
        "size",
        "I"
    );
    //cards
    jfieldID cardsField = (*env)->GetFieldID(
        env,
        deckClass,
        "cards",
        "[Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Card;"
    );
    //top_card
    jfieldID top_cardField = (*env)->GetFieldID(
        env,
        deckClass,
        "top_card",
        "Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Card;"
    );

    (*env)->SetIntField(env, jdeck, sizeField, deck->size);

    jclass cardClass = (*env)->FindClass(env,  "com/lucaslpmoura/JNI_Blackjack/CBlackjack$Card");

    jobject jtop_card = (*env)->AllocObject(env, cardClass);
    convert_card_to_obj(env, deck->cards[0], jtop_card);
    (*env)->SetObjectField(env, jdeck, top_cardField, jtop_card);




    jobjectArray jcards = (*env)->NewObjectArray(env, deck->size, cardClass, NULL);



    jfieldID nextField = (*env)->GetFieldID(
        env,
        cardClass,
        "next",
        "Lcom/lucaslpmoura/JNI_Blackjack/CBlackjack$Card;"
    );
    jobject jlast_card = NULL;


    for(int i = 0; i < deck->size; i++){
        jobject jcard = (*env)->AllocObject(env, cardClass);

        convert_card_to_obj(env, deck->cards[i], jcard);

        if(jlast_card != NULL){
            (*env)->SetObjectField(env, jlast_card, nextField, jcard);
        }

        (*env)->SetObjectArrayElement(env, jcards, i, jcard);
        jlast_card = jcard;
    }

    (*env)->SetObjectField(env, jdeck, cardsField, jcards);

};
void convert_obj_to_deck(JNIEnv *env, Deck *deck, jobject jdeck);







// PLAYER FUNTIONS
void convert_obj_to_player(JNIEnv *env, Player *player, jobject jplayer);
void convert_player_to_obj(JNIEnv *env, Player *player, jobject jplayer);






// ACTION FUNCTIONS
void convert_action();