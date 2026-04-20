SELECT pizza_name, price,
	(SELECT pz.name FROM pizzeria AS pz WHERE pz.id = m.pizzeria_id) AS pizzeria_name
	FROM menu AS m
WHERE NOT EXISTS
    (SELECT menu_id FROM person_order WHERE menu_id = m.id)
ORDER BY pizza_name, price;