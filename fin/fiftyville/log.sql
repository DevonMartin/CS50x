-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Use data from Fiftyville specs to know to look in Crime Scene Reports first,
-- for a crime with the date of July 28, 2021 on Humphrey Street.
SELECT *
  FROM crime_scene_reports
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND street LIKE "Humphrey Street";
-- "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today
-- with three witnesses who were present at the time – each of their interview transcripts mentions the bakery."


-- Found out interviews were conducted on the day of the theft, and each witness mentioned the bakery.
SELECT *
  FROM interviews
 WHERE day = 28
   AND  month = 7
   AND year = 2021
   AND transcript LIKE "%bakery%";
-- "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and
-- drive away. If you have security footage from the bakery parking lot, you might want to look for cars that
-- left the parking lot in that time frame." - Ruth
--
-- "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at
-- Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."
-- -Eugene
--
-- "As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the
-- call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket." -Raymond


-- First, get ID from Fiftyville airport to search flights.
SELECT id
  FROM airports
 WHERE city LIKE "%Fiftyville%";
-- Airport ID: 8


-- Search through all flights from Fiftyville the day after the theft and find earliest one.
SELECT id, hour, minute, destination_airport_id
  FROM flights
 WHERE origin_airport_id = 8
   AND year = 2021
   AND month = 7
   AND day = 29;
-- Flight ID: 36
-- Destination Airport ID: 4
-- Time: 8:20 AM


-- Find passengers of the flight to compare to ATM records
SELECT DISTINCT name, id
  FROM people
 WHERE people.passport_number IN
       (SELECT passengers.passport_number
          FROM passengers
         WHERE passengers.flight_id = 36)
ORDER BY name ASC;
-- Bruce   686048
-- Doris   953679
-- Edward  651714
-- Kelsey  560886
-- Kenny   395717
-- Luca    467400
-- Sofia   398010
-- Taylor  449774


-- Find IDs of people who used the ATM on Leggett to withdraw on the date of the theft.
-- Compare to itinerary of flight.
SELECT person_id
  FROM bank_accounts
 WHERE account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE year = 2021
           AND day = 28
           AND month = 7
           AND atm_location LIKE "%Leggett Street%"
           AND transaction_type LIKE "%with%");
-- Possible passengers:
-- Bruce
-- Kenny
-- Luca
-- Taylor


-- Check phone call logs for calls under 1m on day of theft.
SELECT name AS caller
  FROM people
 WHERE phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE duration < 60
           AND day = 28
      ORDER BY phone_calls.id);


-- Check caller and receiver names of those phone calls to compare to passengers.
SELECT phone_calls.id, people.name AS caller, phone_calls.caller, phone_calls.receiver
  FROM people
  JOIN phone_calls ON phone_calls.caller = people.phone_number
  WHERE phone_calls.id IN
        (SELECT id
           FROM phone_calls
          WHERE duration < 60
            AND day = 28)
ORDER BY phone_calls.id;

SELECT phone_calls.id, people.name AS receiver, phone_calls.caller, phone_calls.receiver
  FROM people
  JOIN phone_calls ON phone_calls.receiver = people.phone_number
  WHERE phone_calls.id IN
        (SELECT id
           FROM phone_calls
          WHERE duration < 60
            AND day = 28)
ORDER BY phone_calls.id;
-- Possible caller/receiver combos:
-- Bruce/Robin  ID: 233
-- Taylor/James ID: 254
-- Kenny/Doris  ID: 279


-- Compare license plates from Bakery Security Logs to possible callers.
SELECT name
  FROM people
 WHERE license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE day = 28
           AND hour = 10
           AND minute BETWEEN 15 AND 25);
-- Bruce is the only caller who left the bakery within 10m of the theft,
-- making him the thief and Robin the accomplice.


-- Check destination airport location from Bruce's flight
SELECT city
  FROM airports
 WHERE id = 4;
 -- City = NYC