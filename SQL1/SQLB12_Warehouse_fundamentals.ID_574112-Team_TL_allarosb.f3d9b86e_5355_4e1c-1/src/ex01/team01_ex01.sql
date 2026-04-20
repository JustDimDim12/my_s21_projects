insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

WITH pre_handler AS (
	SELECT b.*,     COALESCE(
        (SELECT updated 
         FROM currency c 
         WHERE c.id = b.currency_id 
           AND c.updated <= b.updated 
         ORDER BY c.updated DESC 
         FETCH FIRST 1 ROW ONLY),
        (SELECT updated 
         FROM currency c 
         WHERE c.id = b.currency_id 
         ORDER BY c.updated
         FETCH FIRST 1 ROW ONLY)
    ) AS c_up
	FROM balance AS b
),
handler AS (
	SELECT ph.user_id, c.name AS currency_name, TRIM_SCALE(c.rate_to_usd * ph.money) AS currency_in_usd
	FROM pre_handler AS ph
		JOIN currency AS c ON ph.currency_id = c.id AND ph.c_up = c.updated
)
SELECT COALESCE(u.name, 'not defined') AS name, COALESCE(u.lastname, 'not defined') AS lastname,
	h.currency_name, h.currency_in_usd
FROM handler AS h
	FULL JOIN "user" AS u ON u.id = h.user_id
WHERE h.currency_name IS NOT NULL 
	AND h.currency_in_usd IS NOT NULL
ORDER BY name DESC, lastname, currency_name;