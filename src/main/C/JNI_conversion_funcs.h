#ifndef JNI_CONVERSION_FUNCS_H
#define JNI_CONVERSION_FUNCS_H

#include "JNI_blackjack.h"

void convert_card_to_obj(JNIEnv *env, Card *card, jobject jcard);
void convert_obj_to_card(JNIEnv *env, Card *card, jobject jcard);



void convert_obj_to_hand(JNIEnv *env, Hand *hand, jobject jhand);


void convert_deck_to_obj(JNIEnv *env, Deck *deck, jobject jdeck);
void convert_obj_to_deck(JNIEnv *env, Deck *deck, jobject jdeck);

void convert_obj_to_player(JNIEnv *env, Player *plater, jobject jplayer);
void convert_player_to_obj(JNIEnv *env, Player *player, jobject jplayer);

void convert_obj_to_action(JNIEnv *env, Action *action, jobject jaction);
void convert_action_to_obj(JNIEnv *env, Action *action, jobject jaction);

#endif