SELECT name
FROM (SELECT * FROM person
	WHERE gender = 'female' AND age > 25)
ORDER BY name;