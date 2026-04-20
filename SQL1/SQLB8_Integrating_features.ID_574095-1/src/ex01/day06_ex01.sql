WITH m_pz_id AS (
	SELECT m.id AS menu_id, pizzeria_id
	FROM menu AS m JOIN pizzeria AS pz ON m.pizzeria_id = pz.id
	GROUP BY pizzeria_id, menu_id
)
INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT ROW_NUMBER() OVER() AS id, person_id, pizzeria_id,
	(CASE
		WHEN COUNT(po.person_id) = 1
		THEN 10.5
		WHEN COUNT(po.person_id) = 2
		THEN 22
		ELSE 30
	END)
FROM person_order AS po
    JOIN m_pz_id AS mpz ON mpz.menu_id = po.menu_id
GROUP BY po.person_id, mpz.pizzeria_id
ORDER BY person_id;