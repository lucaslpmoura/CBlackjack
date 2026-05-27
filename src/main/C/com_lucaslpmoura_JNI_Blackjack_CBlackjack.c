#include "com_lucaslpmoura_JNI_Blackjack_CBlackjack.h"
#include "JNI_conversion_funcs.h"

JNIEXPORT jint JNICALL Java_com_lucaslpmoura_JNI_1Blackjack_CBlackjack_calculateHandScore
  (JNIEnv *env, jobject this, jobject jhand) {
    Hand *hand = convert_hand(env, jhand);

    return (jint)calculate_hand_score(hand);
 }