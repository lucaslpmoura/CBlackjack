package com.lucaslpmoura.JNI_Blackjack;

import java.util.ArrayList;
import java.util.Scanner;

public class Blackjack {



    public static void main(String args[]){
        CBlackjack.Deck deck = new CBlackjack.Deck();
        CBlackjack.Player gambler = new CBlackjack.Player();
        CBlackjack.Player dealer = new CBlackjack.Player();
        CBlackjack.GameState state = CBlackjack.GameState.NOT_FINISHED;

        System.loadLibrary("blackjack");
        CBlackjack lib = new CBlackjack();
        lib.initializeGame(deck, gambler, dealer);

        String op = "";
        CBlackjack.Action action = CBlackjack.Action.STAND;
        Scanner sc = new Scanner(System.in);

        while(state == CBlackjack.GameState.NOT_FINISHED){
            System.out.println("DEALER");
            print_hand(dealer.hand, lib);
            System.out.println("GAMBLER");
            print_hand(gambler.hand, lib);
            System.out.println("(H)it, (S)tand or (F)old? ");
            op = sc.next();

            switch (op){
                case "H" -> action = CBlackjack.Action.HIT;
                case "S" -> action = CBlackjack.Action.STAND;
                case "F" -> action = CBlackjack.Action.FOLD;
            }
            state = lib.processAction(deck, gambler, dealer, action);
        }

        sc.close();
        print_hand(dealer.hand, lib);
        print_hand(gambler.hand, lib);
        print_game_state(state);
    }

    static void print_hand(CBlackjack.Hand hand, CBlackjack lib) {
        System.out.println("Score: " + lib.calculateHandScore(hand));
        for (int i = 0; i < hand.num_of_cards; i++) {
            print_card(hand.cards[i]);
        }
    }

    static void print_card (CBlackjack.Card card){
        if(card.is_hidden){
            System.out.println("X  X\n\nX  X");
        }else{
            System.out.println(value_to_string(card.value)  + "  " + suit_to_string(card.suit) + "\n\n" + suit_to_string(card.suit) + "  " + value_to_string(card.value));
        }

        System.out.println("\n");
    }

    static String value_to_string(CBlackjack.Value value){
        switch (value){
            case ACE -> {return "A";}
            case JACK -> {return "J";}
            case QUEEN -> {return "Q";}
            case KING  -> {return  "K";}
            default -> {
                return String.valueOf(value.ordinal() + 1);
            }
        }
    }

    static String suit_to_string(CBlackjack.Suit suit){
        return switch (suit) {
            case DIAMONDS -> "♢";
            case CLUBS -> "♧";
            case HEARTS -> "♡";
            case SPADES -> "♤";
        };
    }

    static void print_game_state(CBlackjack.GameState state){
        String s = "";
        switch (state){
            case NOT_FINISHED -> {
                s = "The game is ongoing!";
            }
            case GAMBLER_WINS -> {
                s = "The gambler has won!";
            }
            case DEALER_WINS -> {
                s = "The house wins.";
            }
            case TIE -> {
                s = "It is a tie!";
            }
        }
        System.out.println(s);
    }
}
