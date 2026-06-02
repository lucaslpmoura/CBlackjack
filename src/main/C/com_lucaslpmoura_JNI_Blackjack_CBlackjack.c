#include "com_lucaslpmoura_JNI_Blackjack_CBlackjack.h"
#include "JNI_conversion_funcs.h"

#include <stdlib.h>

JNIEXPORT jint JNICALL Java_com_lucaslpmoura_JNI_1Blackjack_CBlackjack_calculateHandScore
(JNIEnv *env, jobject this, jobject jhand) {
    Hand *hand = malloc(sizeof(Hand));

    convert_obj_to_hand(env, hand, jhand);

    jint hand_score = (jint)calculate_hand_score(hand);

    free_hand(hand);

    return hand_score;
}


JNIEXPORT void JNICALL Java_com_lucaslpmoura_JNI_1Blackjack_CBlackjack_initializeGame
(JNIEnv *env, jobject this, jobject jdeck, jobject jgambler, jobject jdealer){

    Deck *deck = malloc(sizeof(Deck));

    Player *gambler = malloc(sizeof(Player));
    Player *dealer = malloc(sizeof(Player));

    initialize_game(deck, gambler, dealer);


    convert_deck_to_obj(env,deck, jdeck);
    convert_player_to_obj(env, gambler, jgambler);
    convert_player_to_obj(env, dealer, jdealer);

    free_player(gambler);
    free_player(dealer);
    free_deck(deck);
}


