package com.lucaslpmoura.JNI_Blackjack;

public class CBlackjack {

    public enum Suit {
        DIAMONDS,
        CLUBS,
        HEARTS,
        SPADES
    }

    public enum Value {
        ACE,
        TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    }
    public static enum Action {
        HIT, STAND, FOLD
    }

    public static enum Role {
        DEALER, GAMBLER
    }

    public static enum GameState{
        NOT_FINISHED, GAMBLER_WINS, DEALER_WINS, TIE
    }
    public static class Card {
        public Suit suit;
        public Value value;
        private Card next;
        public boolean is_hidden;
    }

    private static final int MAX_DECK_SIZE = 52;

    public static class Deck {
        public int size;
        public Card[] cards = new Card[MAX_DECK_SIZE];
        public Card top_card;
    }

    public static class Hand{
        public int size;
        public Card[] cards;
        public char num_of_cards;
    }

    public static class Player {
        public Role role;
        public Hand hand;
        int score;
    }

    public native void initializeGame(Deck deck, Player gambler, Player dealer);
    public native GameState processAction(Deck deck, Player gambler, Player dealer, Action action);
    public native int calculateHandScore(Hand hand);
}
