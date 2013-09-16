/* 
 * File:   session.h
 * Author: anurag
 *
 * Created on September 16, 2013, 2:56 AM
 */

#ifndef SESSION_H
#define	SESSION_H

class Session
  {
    /* PURPOSE: Manage a session with a single user.
    */

    public:

        Session(int cardNumber, ATM & atm, Bank & bank);

        // Run session until user is through or some exceptional condition
        // prevents further processing

        void doSessionUseCase();

        // Force user to re-enter PIN if bank says original PIN was invalid.
        // Return final code from resubmission to bank.

        Status::Code doInvalidPINExtension();

        // Report a failed transaction to the user, and ask if he/she wants
        // to do another.
     
        bool doFailedTransactionExtension(Status::Code reason);
     
        // Each transation obtains this information from the session when it
        // is needed

        int cardNumber() const;
        int PIN() const;

    private:

        int                       _cardNumber;
        ATM &                     _atm;
        Bank &                    _bank;
        enum { RUNNING, FINISHED, ABORTED }
                                  _state;
        int                       _PIN;
        Transaction *             _currentTransaction;
  };

#endif	/* SESSION_H */

