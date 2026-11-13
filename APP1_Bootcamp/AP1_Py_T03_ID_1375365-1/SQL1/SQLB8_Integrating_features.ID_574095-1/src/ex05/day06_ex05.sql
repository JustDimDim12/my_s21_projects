COMMENT ON TABLE person_discounts IS
	'В данной таблице хранятся данные о том, какие скидки имеются для конкретных покупателей и в каких пиццериях';
COMMENT ON COLUMN person_discounts.id IS 'Уникальный идентификатор записи о скидке (первичный ключ)';
COMMENT ON COLUMN person_discounts.person_id IS 'Идентификатор конкретного покупателя';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Идентификатор конкретной пиццерии';
COMMENT ON COLUMN person_discounts.discount IS
	'Идентификатор скидки, выдаваемой конкретному покупателю в конкретной пиццерии';