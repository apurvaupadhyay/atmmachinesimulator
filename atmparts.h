/* 
 * File:   atmparts.h
 * Author: anurag
 *
 * Created on September 16, 2013, 12:46 AM
 */

#ifndef ATMPARTS_H
#define	ATMPARTS_H

class CardReader
  {
    /* 
     * PURPOSE: Model the ATM component that reads a customer's card
     */

    public:

        CardReader();

        void ejectCard();
        void retainCard();

        enum ReaderStatus 
          { NO_CARD, UNREADABLE_CARD, CARD_HAS_BEEN_READ };

        ReaderStatus checkForCardInserted();
        int cardNumber() const;

    private:

        ReaderStatus    _status;
        int             _cardNumberRead;        
  };

  class Display
  {
    /* 
     * PURPOSE: Model the ATM component that displays messages for the customer
     */

    public:

        Display();

        // The following display screens calling for the customer to take a
        // specific action
     
        void requestCard();
        void requestPIN();
        void displayMenu(const char * whatToChoose,
                         int numItems,
                         const char * items[]);
        void requestAmountEntry();
        void requestDepositEnvelope();
     
        // The following displays a screen reporting the customer's card
        // is unreadable
     
        void reportCardUnreadable();
    
        // The following displays a screen reporting why a transaction
        // failed, and asking if customer wants another.
      
        void reportTransactionFailure(const char * explanation);

        // The following are used in case the customer's PIN was incorrect
     
        void requestReEnterPIN();
        void reportCardRetained();

       // The following is used by the Keyboard to echo input as typed

       void echoInput(const char * echo);

       // Clear off the screen after a display has been seen

        void clearDisplay();
  };
  
  class Keyboard
  {
    /* 
     * PURPOSE: Model the ATM component that accepts input from the customer
     */

    public:

        Keyboard();

        int readPIN(Display & echoOn);
        int readMenuChoice(int numItems);
        Money readAmountEntry(Display & echoOn);
  };
  
  class CashDispenser
  {
    /* 
     * PURPOSE: Model the ATM component that dispenses cash during withdrawls
     */

    public:

        CashDispenser();

        void setCash(Money initialCash);
        void dispenseCash(Money amount);
        Money currentCash() const;

    private:

        Money _currentCash;
  };
  class EnvelopeAcceptor
  {
    /* 
     * PURPOSE: Model the ATM component that accepts an envelope during deposits
     */

    public:

        EnvelopeAcceptor();

        bool acceptEnvelope();
  };

  class ReceiptPrinter
  {
    /* 
     * PURPOSE: Model the ATM component that prints receipts
     */

    public:

        ReceiptPrinter();

        void printReceipt(int theATMnumber,
                          const char * theATMlocation,
                          int cardNumber,
                          int serialNumber,
                          const char * description,
                          Money amount,
                          Money balance,
                          Money availableBalance);
  };

  class OperatorPanel
  {
    /* 
     * PURPOSE: Model the ATM component that allows an operator to stop
     *          the machine for maintenance
     */

    public:

        OperatorPanel();

        bool switchOn();                // True iff "on"
        Money getInitialCash();
  };


#endif	/* ATMPARTS_H */

