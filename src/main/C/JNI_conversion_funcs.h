#ifndef JNI_CONVERSION_FUNCS_H
#define JNI_CONVERSION_FUNCS_H

#include "JNI_blackjack.h"

Card *convert_card(JNIEnv *env, jobject jcard);
Hand *convert_hand(JNIEnv *env, jobject jhand);
Deck *convert_deck();
Player *convert_player();
Action *convert_action();

#endif