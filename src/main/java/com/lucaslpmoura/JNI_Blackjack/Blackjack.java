package com.lucaslpmoura.JNI_Blackjack;

import java.util.ArrayList;

public class Blackjack {



    public static void main(String args[]){

        CBlackjack.Card card1 = new CBlackjack.Card();
        CBlackjack.Card card2 = new CBlackjack.Card();

        card1.suit = CBlackjack.Suit.CLUBS;
        card1.value = CBlackjack.Value.ACE;
        card1.is_hidden = false;

        card2.suit = CBlackjack.Suit.DIAMONDS;
        card2.value = CBlackjack.Value.FOUR;
        card2.is_hidden = false;

        CBlackjack.Hand hand = new CBlackjack.Hand();
        hand.size = 2;
        hand.cards = new CBlackjack.Card[hand.size];
        hand.cards[0] = card1;
        hand.cards[1] = card2;
        hand.num_of_cards = 2;

        System.loadLibrary("blackjack");
        var lib = new CBlackjack();
        int score = lib.calculateHandScore(hand);

        System.out.println("Score: " + score);

        CBlackjack.Deck deck = new CBlackjack.Deck();
        CBlackjack.Player gambler = new CBlackjack.Player();
        CBlackjack.Player dealer = new CBlackjack.Player();

        lib.initializeGame(deck, gambler, dealer);
        System.out.println(deck.top_card.suit);


    }
}
