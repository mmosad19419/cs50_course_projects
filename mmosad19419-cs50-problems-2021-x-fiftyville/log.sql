-- Keep a log of any SQL queries you execute as you solve the mystery.
 -- schema the crime_scene table
.schema crime_scene_reports

-- get the description of the theft
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- take a look at the interview text with the witnesses
-- schema the interview table
.schema interviews
-- select name of witness and the transcript of his interview
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28;
-- i get three name (Ruth|Eugene|Raymond|)
-- i used eugene words and checked the atm_transaction
.schema atm_transactions
SELECT account_number,amount,transaction_type FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = "Fifer Street";
-- and i get all the bank account who made a withdraw this day and get there data from people table
.schema people
the suspects
-- Danielle|(389) 555-5198|8496433585
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 28500762;
-- Bobby|(826) 555-1652|9878712108
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 28296815;
-- Madison|(286) 555-6063|1988161715
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 76054385;
-- Ernest|(367) 555-5533|5773159633
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 49610011;
-- Roy|(122) 555-4581|4408372428
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 49610011;
-- Elizabeth|(829) 555-5269|7049073643
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 25506511;
-- Victoria|(338) 555-6650|9586786673
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 81061156;
-- Russell|(770) 555-1861|3592750733
SELECT name, phone_number, passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = 26013199;

-- then i go after Raymond interview transcript and checked the phone calls of this day and check it with the phone number of the suspects
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28;
-- get the data of the caller and reciever
-- i get the result
-- Bobby|(826) 555-1652|9878712108 called  Doris|(066) 555-9701|7214083635 |55 sec
SELECT name, passport_number FROM people WHERE  phone_number = "(066) 555-9701";
-- Madison|(286) 555-6063|1988161715 called James||(676) 555-6554|2438825627|43 sec
SELECT name, passport_number FROM people WHERE  phone_number = "(676) 555-6554";
-- Ernest|(367) 555-5533|5773159633 called Berthold|(375) 555-8161|45 sec
SELECT name, passport_number FROM people WHERE  phone_number = "(375) 555-8161";
-- Russell|(770) 555-1861|3592750733 called Philip|(725) 555-3243|3391710505|49 sec
SELECT name, passport_number FROM people WHERE  phone_number = "(725) 555-3243";
-- Victoria|(338) 555-6650|9586786673 called Anna|(704) 555-2131|54 sec
SELECT name, passport_number FROM people WHERE  phone_number = "(704) 555-2131";

-- Then i checked who leave fiftyville taking a flight the next day
-- by checking all the passport number that left the next day
SELECT passport_number FROM passengers
JOIN flights ON flight_id = flights.id
WHERE origin_airport_id = 8 AND year = 2020 AND day = 29 AND month = 7 ORDER BY passport_number;
-- i found who left was:
-- Bobby -- Doris
-- Ernest
-- Victoria -- Philip
-- Madison -- James

-- Now i will use Ruth interview transcript and konw who from these people was in the court house
-- Checking for the License_plate and get the name of the owner of it:
SELECT name FROM people
WHERE
license_plate IN
("94KL13X","6P58WS2", "R3G7486", "13FNH73", "5P2BI95","4328GD8","G412CB7","L93JTIZ","322W7JE","V47T75I","WD5M8I6","NRYN856","1106N58","0NTHK55");
-- i get these names:
-- Patrick - Danielle - Ernest - Amber - Russell - Jeremy - Brandon - Evelyn - Elizabeth - Denise - Roger - Thomas - Madison - Sophia

-- So the common one between all of this is (Ernest) and he called (Berthold) but he left alone and went to (London).







