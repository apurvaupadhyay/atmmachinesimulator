/*
 * Example ATM simulation - file atm.cc
 *
 * This file implements the class that manages the ATM itself
 * - as declared in atm.h
 *
 *
 */

#include "sysdep.h"
#include "status.h"
#include "money.h"
#include "bank.h"
#include "session.h"
#include "transaction.h"
#include "atmparts.h"
#include "atm.h"


//

ATM::ATM(int number, const char * location, Bank & bank)
  : _number(number),
    _location(location),
    _bank(bank),
    _state(STOPPED),
    _cardReader(* new CardReader()),
    _display(* new Display()),
    _keyboard(* new Keyboard()),
    _cashDispenser(* new CashDispenser()),
    _envelopeAcceptor(* new EnvelopeAcceptor),
    _receiptPrinter(* new ReceiptPrinter()),
    _operatorPanel(* new OperatorPanel())
  { }


//

Money ATM::startupOperation()
  { 
    // Wait for switch to be turned on
    while (! _operatorPanel.switchOn()) 
        ;
    _state = RUNNING;
    return _operatorPanel.getInitialCash(); 
  }

//


void ATM::serviceCustomers(Money initialCash)
  {
    _cashDispenser.setCash(initialCash);

    while (_state == RUNNING)
      { 
        CardReader::ReaderStatus readerStatus;

        _display.requestCard();
        do
          { 
            if (! _operatorPanel.switchOn())
                _state = STOPPED;
            else
                readerStatus = _cardReader.checkForCardInserted();
          }
        while (_state == RUNNING && readerStatus == CardReader::NO_CARD);
        _display.clearDisplay();
         
        if (_state == RUNNING)
          switch (readerStatus)
            {
              case CardReader::CARD_HAS_BEEN_READ:      
                {
                  Session * session = new Session(_cardReader.cardNumber(),
                                                  * this,
                                                  _bank);
                  session -> doSessionUseCase();
                  delete session;

                  break;
                }

              case CardReader::UNREADABLE_CARD:

                _display.reportCardUnreadable();
                _cardReader.ejectCard();
            }
      }
  }


//


int ATM::getPIN() const
  { _display.requestPIN();
    int PIN = _keyboard.readPIN(_display);
    _display.clearDisplay();
    return PIN;
  }


//


int ATM::getMenuChoice(const char * whatToChoose,
                       int numItems,
                       const char * items[]) const
  { _display.displayMenu(whatToChoose, numItems, items);
    int choice =  _keyboard.readMenuChoice(numItems);
    _display.clearDisplay();
    return choice;
  }


//


Money ATM::getAmountEntry() const
  { _display.requestAmountEntry();
    Money amount = _keyboard.readAmountEntry(_display);
    _display.clearDisplay();
    return amount;
  }


//


bool ATM::checkIfCashAvailable(Money amount) const
  { return ! (_cashDispenser.currentCash() < amount);
  }


//


void ATM::dispenseCash(Money amount) const
  { _cashDispenser.dispenseCash(amount);
  }


//


bool ATM::acceptEnvelope() const
  { return _envelopeAcceptor.acceptEnvelope(); 
  }


//


void ATM::issueReceipt(int cardNumber,
                       int serialNumber,
                       const char * description,
                       Money amount,
                       Money balance,
                       Money availableBalance) const
  { 
    _receiptPrinter.printReceipt(_number, _location, cardNumber, serialNumber,
                                 description, amount,
                                 balance, availableBalance);;
  }


//


int ATM::reEnterPIN() const
  { _display.requestReEnterPIN();
    int PIN = _keyboard.readPIN(_display);
    _display.clearDisplay();
    return PIN;
  }


//


bool ATM::reportTransactionFailure(const char * explanation) const
  {
    _display.reportTransactionFailure(explanation);
    int response = _keyboard.readMenuChoice(2);
    _display.clearDisplay();
    return response == 1;
  }


//


void ATM::ejectCard() const
  { _cardReader.ejectCard(); }


//


void ATM::retainCard() const
  { _cardReader.retainCard(); 
    _display.reportCardRetained();
    // The above routine will sleep 20 seconds to let user see message
    _display.clearDisplay();
  }

//


int ATM::number() const
  { return _number; }

//


