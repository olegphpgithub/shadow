
drop view employeeview;

create view employeeview as
    select id as empId, city as cityId, name as name, country as countryId from employee;
    
create view cityview as
    select id as cityMyId, CONCAT(name, "*") as cityMyName from city;