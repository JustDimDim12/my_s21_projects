WITH balance_handler AS (
	SELECT user_id, type, SUM(money) AS volume, currency_id
	FROM balance
	GROUP BY user_id, type, currency_id
),
currency_pre_handler AS (
	SELECT id, MAX(updated) AS updated
	FROM currency
	GROUP BY id
),
currency_handler AS (
	SELECT c.*
	FROM currency_pre_handler AS cph
		NATURAL JOIN currency AS c)
SELECT COALESCE(u.name, 'not defined') AS name, COALESCE(u.lastname, 'not defined') AS lastname, b.type AS type,
	b.volume AS volume, COALESCE(c.name, 'not defined') AS currency_name, COALESCE(c.rate_to_usd, 1) AS last_rate_to_usd,
	TRIM_SCALE(b.volume * COALESCE(c.rate_to_usd, 1)) AS total_volume_in_usd
FROM "user" AS u
	FULL JOIN balance_handler AS b ON u.id = b.user_id
	FULL JOIN currency_handler AS c ON c.id = b.currency_id
ORDER BY name DESC, lastname, type;