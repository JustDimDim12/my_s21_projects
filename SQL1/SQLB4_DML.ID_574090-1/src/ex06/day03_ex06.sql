WITH menu_pz AS (SELECT m.id, pz.name AS pz_name, m.pizza_name, m.price
	FROM menu AS m JOIN pizzeria AS pz ON m.pizzeria_id = pz.id)
SELECT m1.pizza_name, m1.pz_name AS pizzeria_name_1, m2.pz_name AS pizzeria_name_2, m1.price
FROM menu_pz AS m1 
	JOIN menu_pz AS m2 ON m1.pizza_name = m2.pizza_name 
		AND m1.price = m2.price AND m1.id > m2.id
ORDER BY pizza_name;