/* 
 * File:   status.h
 * Author: apurva
 *
 * Created on September 16, 2013, 11:07 AM
 */

#ifndef STATUS_H
#define	STATUS_H

class Status
  {
    public:
   
        enum Code
          { 
            SUCCESS,
               
            // Cash dispenser does not have enough cash for a withdrawl request
            
            TOO_LITTLE_CASH,

            // Customer failed to deposit envelope in allowed time
               
            ENVELOPE_DEPOSIT_TIMED_OUT,
               
            // Various reasons why bank might reject a transaction
               
            UNKNOWN_CARD,    // Card number not recognized
            INVALID_PIN,     // PIN not correct for card
            NO_SUCH_ACCOUNT, // Card holder does not have this type account
            CANT_WITHDRAW_FROM_ACCOUNT,  // Account doesn't allow ATM withdrawl
            INSUFFICIENT_AVAILABLE_BALANCE, // Self-explanatory
            DAILY_WITHDRAWL_LIMIT_EXCEEDED  // Ditto
 
          };
  };

#endif	/* STATUS_H */

