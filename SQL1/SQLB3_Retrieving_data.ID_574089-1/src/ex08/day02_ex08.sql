SELECT p.name
FROM person AS p
	JOIN person_order AS po ON p.id = po.person_id
	JOIN menu AS m ON m.id = po.menu_id
WHERE (p.address = 'Moscow' OR p.address = 'Samara') 
	AND (m.pizza_name = 'pepperoni pizza' OR m.pizza_name = 'mushroom pizza')
	AND p.gender = 'male'	
ORDER BY p.name DESC;