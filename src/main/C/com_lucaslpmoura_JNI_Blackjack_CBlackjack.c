#include "com_lucaslpmoura_JNI_Blackjack_CBlackjack.h"
#include "JNI_conversion_funcs.h"

#include <stdlib.h>

#define CHECK_EXCEPTION() \
    if ((*env)->ExceptionCheck(env)) { \
        (*env)->ExceptionDescribe(env); \
        return NULL; \
    }

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

    free_deck(deck);
    free_player(gambler);
    free_player(dealer);

}

JNIEXPORT jobject JNICALL Java_com_lucaslpmoura_JNI_1Blackjack_CBlackjack_processAction
(JNIEnv *env, jobject this, jobject jdeck, jobject jgambler, jobject jdealer, jobject jaction){
    Deck *deck = malloc(sizeof(Deck));

    Player *gambler = malloc(sizeof(Player));
    Player *dealer = malloc(sizeof(Player));

    Action action = convert_obj_to_action(env, jaction);

    convert_obj_to_deck(env, deck, jdeck);
    convert_obj_to_player(env, gambler, jgambler);
    convert_obj_to_player(env, dealer, jdealer);


    GameState game_state = process_action(deck, gambler, dealer, action);


    convert_deck_to_obj(env, deck, jdeck);

    convert_player_to_obj(env, gambler, jgambler);

    convert_player_to_obj(env, dealer, jdealer);

    free_deck(deck);
    free_player(gambler);
    free_player(dealer);



    jobject jstate = convert_state_to_obj(env, game_state);

    return jstate;

}

