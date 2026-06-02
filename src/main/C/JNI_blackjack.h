//
// Created by lucas on 5/14/26.
//

#ifndef BLACKJACKLIB_JNI_BLACKJACK_H
#define BLACKJACKLIB_JNI_BLACKJACK_H

#include <stddef.h>

#define OK 0
#define ERR_HAND_FULL 1
#define ERR_DECK_EMPTY 2

#define ACE_IN_HAND 11

#define BLACKJACK 21

typedef enum {
    DIAMONDS,
    CLUBS,
    HEARTS,
    SPADES
} Suit;

typedef enum {
    ACE,
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING
} Value;

typedef struct Card {
    Suit suit;
    Value value;
    struct Card *next;
    bool is_hidden;
} Card;

#define DECK_MAX_SIZE 52

typedef struct{
    size_t size;
    Card *cards[DECK_MAX_SIZE];
    Card *top_card;
} Deck;

typedef struct Hand {
    size_t size;
    Card **cards;
    char num_of_cards;
} Hand;

typedef enum {
    GAMBLER = 5,
    DEALER = 2
} Role;

typedef struct  {
    Role role;
    Hand *hand;
    size_t score;
} Player;

typedef enum {
    HIT,
    STAND,
    FOLD
} Action;

typedef enum {
    NOT_FINISHED,
    GAMBLER_WINS,
    DEALER_WINS,
    TIE
} GameState;

size_t calculate_hand_score(const Hand *hand);
void initialize_game(Deck *deck, Player *gambler, Player *dealer);
GameState process_action(Deck *deck, Player *gambler, Player *dealer, Action action);

void free_hand(Hand *hand);
void free_player(Player *player);
void free_deck(Deck *deck);

#endif //BLACKJACKLIB_JNI_BLACKJACK_H