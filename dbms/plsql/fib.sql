CREATE OR REPLACE PROCEDURE fibonacci(num IN NUMBER) AS
    a NUMBER := 0;
    b NUMBER := 1;
    c NUMBER;
BEGIN
    IF num >= 1 THEN
        DBMS_OUTPUT.PUT_LINE(a);
    END IF;

    IF num >= 2 THEN
        DBMS_OUTPUT.PUT_LINE(b);
    END IF;

    FOR i IN 3 .. num LOOP
        c := a + b;
        DBMS_OUTPUT.PUT_LINE(c);
        a := b;
        b := c;
    END LOOP;
END;
/
 
DECLARE
    num NUMBER := 5;
BEGIN
    fibonacci(num);
END;
/
