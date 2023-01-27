SELECT DISTINCT(name) FROM people
JOIN stars ON person_id = people.id
WHERE stars.movie_id IN (SELECT stars.movie_id FROM stars
JOIN people ON person_id = people.id
WHERE people.name = "Kevin Bacon" AND birth = "1958")
EXCEPT
SELECT name FROM people WHERE name = "Kevin Bacon";