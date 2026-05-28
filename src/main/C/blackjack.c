#include "JNI_blackjack.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

Card *generate_card(const Suit suit, const Value value) {
    Card *new_card = malloc(sizeof(Card));
    new_card->suit = suit;
    new_card->value = value;
    new_card->next = NULL;

    new_card->is_hidden = false;

    return new_card;
}

char *suit_to_string(const Suit suit) {
    switch (suit) {
        case DIAMONDS:
            return "♢";
        case CLUBS:
            return "♧";
        case HEARTS:
            return "♡";
        case SPADES:
            return "♤";
    }
    return "/";
}

void value_to_string(const Value value, char *buffer) {
    if (value >= TWO && value <= TEN) {
        // ASCII 0 + 1 (TWO = , THREE, 2...)
        sprintf(buffer,"%c", value + '0' + 1);
    }else {
        if (value == ACE) {
            sprintf(buffer,"%c", 'A');
        }
        if (value == JACK) {
            sprintf(buffer,"%c", 'J');
        }
        if (value == QUEEN) {
            sprintf(buffer,"%c", 'Q');
        }
        if (value == KING) {
            sprintf(buffer,"%c", 'K');
        }
    }
}

void print_card(const Card *card) {
    char *value = malloc(1 + sizeof(char));; // char + '\0
    value_to_string(card->value, value);
    if (card->is_hidden) {
        printf("X  X\n\nX  X");
    }else {
        printf("%s  %s\n\n%s  %s", value, suit_to_string(card->suit), suit_to_string(card->suit), value);
    }

    printf("\n");
    free(value);
}

void *generate_deck(Deck *new_deck) {
    new_deck->top_card = NULL;
    new_deck->size = 0;

    for (char i = DIAMONDS; i <= SPADES; i++) {
        for (size_t j = ACE; j <= KING; j++) {
            Card *new_card = generate_card(i, j);

            new_card->next = new_deck->top_card;
            new_deck->top_card = new_card;

            new_deck->cards[new_deck->size] = new_card;
            new_deck->size++;
        }
    }
    return new_deck;
}

Deck *generate_aces_deck() {
    Deck *new_deck = malloc(sizeof(Deck));
    new_deck->top_card = NULL;
    new_deck->size = 0;

    for (char i = DIAMONDS; i <= SPADES; i++) {
            Card *new_card = generate_card(i, ACE);

            new_card->next = new_deck->top_card;
            new_deck->top_card = new_card;

            new_deck->cards[new_deck->size] = new_card;
            new_deck->size++;
    }
    for (char i = DIAMONDS; i <= SPADES; i++) {
        for (size_t j = JACK; j <= KING; j++) {
            Card *new_card = generate_card(i, j);

            new_card->next = new_deck->top_card;
            new_deck->top_card = new_card;

            new_deck->cards[new_deck->size] = new_card;
            new_deck->size++;
        }
    }

    return new_deck;

}

void shuffle_deck(Deck *deck) {
    for (size_t i = deck->size - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);

        Card *tmp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = tmp;
    }

    for (size_t i = 0; i < deck->size - 1; i++) {
        deck->cards[i]->next = deck->cards[i + 1];
    }

    deck->cards[deck->size - 1]->next = NULL;
    deck->top_card = deck->cards[0];
}


void print_deck(const Deck *deck) {
    Card *card = deck->top_card;
    print_card(card);
    do {
        print_card(card);
        card = card->next;
    }while (card != NULL);
}

void free_deck(Deck *deck) {
    Card *card = deck->top_card;
    do {
        Card *next_card = card->next;
        free(card);
        card = next_card;
    }while (card != NULL);

    free(deck);
}


Hand *generate_hand(size_t hand_size) {
    Hand *new_hand = malloc(sizeof(Hand));
    new_hand->size = hand_size;

    new_hand->cards = (Card**) malloc(sizeof(Card*) * new_hand->size);

    for (size_t i = 0; i < new_hand->size; i++) {
        new_hand->cards[i] = NULL;
    }
    return new_hand;
}

size_t calculate_card_score(const Card *card) {
    if (card->is_hidden) {
        return 0;
    }

    switch (card->value) {
        case ACE:
            return ACE_IN_HAND;
        case KING:
        case QUEEN:
        case JACK:
            return 10;

        default:
            return card->value + 1;
    }

}



void reveal_all_hand_cards(const Hand *hand) {
    for (char i = 0; i < hand->size; i++) {
        hand->cards[i]->is_hidden = false;
    }
}

void print_hand(const Hand *hand) {
    printf("Num of. cards: %d\n", hand->num_of_cards);
    printf("Score: %lu\n", calculate_hand_score(hand));
    for (size_t i = 0; i < hand->num_of_cards; i++) {
        print_card(hand->cards[i]);
    }
}

void free_hand(Hand *hand) {
    for (size_t i = 0; i < hand->size; i++) {
        if (hand->cards[i] != NULL) {
            free(hand->cards[i]);
        }
    }

    free(hand);
}

size_t add_card(Hand *hand, Card *card, bool is_hidden) {
    for (size_t i = 0; i < hand->size; i++) {
        if (hand->cards[i] == NULL) {
            card->is_hidden = is_hidden;
            hand->cards[i] = card;
            hand->num_of_cards++;
            return OK;
        }
    }
    return ERR_HAND_FULL;
}

size_t deal_card(Deck *deck, Player *player) {
    Card *card = deck->top_card;
    if (card == NULL) {
        return ERR_DECK_EMPTY;
    }
    deck->top_card = deck->top_card->next;
    return add_card(player->hand, card, false);
}

size_t deal_hidden_card(Deck *deck, Player *player) {
    Card *card = deck->top_card;
    if (card == NULL) {
        return ERR_DECK_EMPTY;
    }
    deck->top_card = deck->top_card->next;
    return add_card(player->hand, card, true);
}

Player *generate_player(Role role){
    Player *new_player = malloc(sizeof(Player));
    new_player->role = role;
    new_player->hand = generate_hand(role);
    new_player->score = 0;
    return new_player;
}

void calculate_player_score(Player *player) {
    player->score =  calculate_hand_score(player->hand);
}

void print_player(const Player *player) {
    if (player->role == GAMBLER) {
        printf(" --- GAMBLER ---\n\n");
    }
    if (player->role == DEALER) {
        printf(" --- DEALER ---\n\n");
    }

    print_hand(player->hand);
    printf("----------\n\n");
}

void free_player(Player *player) {
    free_hand(player->hand);
    free(player);
}

GameState process_match_state(Player *gambler, Player *dealer, Action action) {
    calculate_player_score(gambler);
    calculate_player_score(dealer);

    switch (action) {
        case HIT:
            if (gambler->score > BLACKJACK) {
                return DEALER_WINS;
            }
            return NOT_FINISHED;

        case STAND:
            if ((gambler->score > BLACKJACK && dealer->score > BLACKJACK) || (gambler->score == dealer->score)) {
                return TIE;
            }
            if (
                gambler->score > BLACKJACK ||
                dealer->score < BLACKJACK && dealer->score > gambler->score
                ) {
                return DEALER_WINS;
                }else {
                    return GAMBLER_WINS;
                }
        case FOLD:
            return DEALER_WINS;

        default:
            return NOT_FINISHED;
    }
}

void initialize_game(Deck *deck, Player *gambler, Player *dealer){
    srand(time(NULL));

    gambler = generate_player(GAMBLER);
    dealer = generate_player(DEALER);

    generate_deck(deck);
    shuffle_deck(deck);

    deal_card(deck, dealer);
    deal_card(deck, gambler);
    deal_hidden_card(deck, dealer);
}


GameState process_action(Deck *deck, Player *gambler, Player *dealer, Action action) {
    switch (action) {
        case HIT:
            deal_card(deck, gambler);
            break;
        case STAND:
            reveal_all_hand_cards(dealer->hand);
            break;
        case FOLD:
        default:
    }
    return process_match_state(gambler, dealer, action);
}

size_t calculate_hand_score(const Hand *hand) {

    size_t score = 0;
    size_t num_of_aces = 0;
    for (size_t i = 0; i < hand->num_of_cards; i++) {
        const size_t card_score = calculate_card_score(hand->cards[i]);

        if (card_score == ACE_IN_HAND) {
            num_of_aces++;
        }else {
            score += card_score;
        }
    }

    /*
    * If the card is an Ace, it can be worth either 1 or 11.
    * It is only worth 11 if it wouldn't push the hand score past BLACKJACK.
    */
    if (score + num_of_aces*11 > BLACKJACK) {
        return score + num_of_aces;
    }else {
        return score + num_of_aces*11;
    }
}


