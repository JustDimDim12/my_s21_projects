SELECT pz.name, COUNT(pz.name) AS count_of_orders, ROUND(AVG(m.price), 2) AS average_price, 
    MAX(m.price) AS max_price, MIN(m.price) AS min_price
FROM menu AS m 
	JOIN person_order AS po ON m.id = po.menu_id
	JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
GROUP BY name
ORDER BY name;