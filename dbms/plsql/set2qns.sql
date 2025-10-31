-- Display each center with total number of students allotted (using Cursor)
DECLARE
  CURSOR c_center IS
    SELECT c.center_id, c.center_name, COUNT(a.allot_id) AS total_students
    FROM CENTER c
    LEFT JOIN ALLOTMENT a ON c.center_id = a.center_id
    GROUP BY c.center_id, c.center_name;
  rec c_center%ROWTYPE;
BEGIN
  DBMS_OUTPUT.PUT_LINE('Center ID | Center Name | Total Students');
  OPEN c_center;
  LOOP
    FETCH c_center INTO rec;
    EXIT WHEN c_center%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE(rec.center_id || ' | ' || rec.center_name || ' | ' || rec.total_students);
  END LOOP;
  CLOSE c_center;
END;
/



-- Trigger to prevent allotting a student if the center is already full
CREATE OR REPLACE TRIGGER trg_prevent_overallot
BEFORE INSERT ON ALLOTMENT
FOR EACH ROW
DECLARE
  v_capacity CENTER.capacity%TYPE;
  v_current_count NUMBER;
BEGIN
  SELECT capacity INTO v_capacity FROM CENTER WHERE center_id = :NEW.center_id;
  SELECT COUNT(*) INTO v_current_count FROM ALLOTMENT WHERE center_id = :NEW.center_id;
  IF v_current_count >= v_capacity THEN
    RAISE_APPLICATION_ERROR(-20001, 'Center capacity full. Cannot allot student.');
  END IF;
END;
/

-- Trigger to automatically assign rank based on total marks
CREATE OR REPLACE TRIGGER trg_assign_rank
AFTER INSERT OR UPDATE OF total_marks ON STUDENT
DECLARE
  v_rank NUMBER := 0;
BEGIN
  FOR rec IN (
    SELECT student_id FROM STUDENT ORDER BY total_marks DESC
  ) LOOP
    v_rank := v_rank + 1;
    UPDATE STUDENT
    SET rank = v_rank
    WHERE student_id = rec.student_id;
  END LOOP;
END;
/

-- Procedure: Display students who scored above average total marks of their city
CREATE OR REPLACE PROCEDURE show_above_avg_city AS
BEGIN
  DBMS_OUTPUT.PUT_LINE('Students scoring above average marks of their city:');
  FOR rec IN (
    SELECT stud_id, stud_name, city, total_marks
    FROM STUDENT s
    WHERE total_marks > (
      SELECT AVG(total_marks)
      FROM STUDENT
      WHERE city = s.city
    )
  ) LOOP
    DBMS_OUTPUT.PUT_LINE(
      'ID: ' || rec.stud_id ||
      ', Name: ' || rec.stud_name ||
      ', City: ' || rec.city ||
      ', Marks: ' || rec.total_marks
    );
  END LOOP;
END;
/
