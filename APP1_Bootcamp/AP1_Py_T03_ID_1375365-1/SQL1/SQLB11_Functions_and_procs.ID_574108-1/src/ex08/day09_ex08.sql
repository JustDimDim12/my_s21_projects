CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INTEGER DEFAULT 10) RETURNS TABLE(fibonacci BIGINT) AS $$
	DECLARE
		count INTEGER := 1;
		val BIGINT;
		past_val1 BIGINT := 1;
		past_val2 BIGINT := 0;
	BEGIN
		LOOP
	        EXIT WHEN past_val1 + past_val2 > pstop;
			IF count = 1 THEN
            	val := 0;
        	ELSIF count = 2 THEN
            	val := 1;
        	ELSE
            	val := past_val1 + past_val2;
        	END IF;

			fibonacci := val;
        	RETURN NEXT;
			
			past_val2 := past_val1;
        	past_val1 := val;
	        count := count + 1;
    	END LOOP;

		RETURN;	
	END;
$$ LANGUAGE plpgsql;

select * from fnc_fibonacci(100);
select * from fnc_fibonacci();