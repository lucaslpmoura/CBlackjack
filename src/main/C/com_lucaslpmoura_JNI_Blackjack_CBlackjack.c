#include "com_lucaslpmoura_JNI_Blackjack_CBlackjack.h"
#include "JNI_conversion_funcs.h"

#include <stdlib.h>

JNIEXPORT jint JNICALL Java_com_lucaslpmoura_JNI_1Blackjack_CBlackjack_calculateHandScore
(JNIEnv *env, jobject this, jobject jhand) {
    Hand *hand = convert_hand(env, jhand);

    return (jint)calculate_hand_score(hand);
}


JNIEXPORT void JNICALL Java_com_lucaslpmoura_JNI_1Blackjack_CBlackjack_initializeGame
(JNIEnv *env, jobject this, jobject deckObj, jobject gamblerObj, jobject dealerObj){

    Deck *deck = malloc(sizeof(Deck));

    Player *gambler = malloc(sizeof(Player));
    Player *dealer = malloc(sizeof(Player));

}


