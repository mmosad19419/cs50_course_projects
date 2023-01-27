SELECT AVG(rating) FROM ratings
JOIN movies ON id = ratings.movie_id
WHERE year = 2012;