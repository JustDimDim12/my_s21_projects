CREATE OR REPLACE FUNCTION fnc_trg_person_audit() RETURNS trigger AS $person_audit$
    BEGIN
		IF (TG_OP = 'INSERT') THEN
            INSERT INTO person_audit
                    SELECT
                         now(),
                         'I',
                         new.id, new.name, new.age, new.gender, new.address;
		ELSIF (TG_OP = 'UPDATE') THEN
            INSERT INTO person_audit
                    SELECT
                         now(),
                         'U',
                         old.id, old.name, old.age, old.gender, old.address;
		ELSIF (TG_OP = 'DELETE') THEN
            INSERT INTO person_audit
                    SELECT
                         now(),
                         'D',
                         old.id, old.name, old.age, old.gender, old.address;
        END IF;
        RETURN NULL;
    END;
$person_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_audit AFTER INSERT OR UPDATE OR DELETE
    ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_audit();

DELETE FROM person_audit;
DROP TRIGGER IF EXISTS trg_person_insert_audit ON person;
DROP TRIGGER IF EXISTS trg_person_update_audit ON person;
DROP TRIGGER IF EXISTS trg_person_delete_audit ON person;

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk'); 
UPDATE person SET name = 'Bulat' WHERE id = 10; 
UPDATE person SET name = 'Damir' WHERE id = 10; 
DELETE FROM person WHERE id = 10;