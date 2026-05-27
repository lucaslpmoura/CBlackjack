#include <stdlib.h>
#include <stdbool.h>
#include <jni.h>

#include "JNI_conversion_funcs.h"

Card *convert_card(JNIEnv *env, jobject jcard){
    if(jcard == NULL) return NULL;

    Card *card = malloc(sizeof(Card));

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

    card->next = NULL;

    return card;
}

Hand *convert_hand(JNIEnv *env, jobject jhand) {
    if(jhand == NULL) return NULL;

    Hand *hand = malloc(sizeof(Hand));

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
        hand->cards[i] = convert_card(env, jcard);
    }

    return hand;
}
Deck *convert_deck();
Player *convert_player();
Action *convert_action();