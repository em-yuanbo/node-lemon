var node_lemon= require('./');

/*
 * rs :
 * {
 *  type:'select|update|delete|insert|replace|createtable|droptable|set|show|setnames|unknown'
 *
 * }
 *
 */
var types = require('./src/type');
var sqls = [
  //"CREATE DATABASE database_name",
  "CREATE TABLE Persons ( Id_P int, LastName varchar(255))",
  //"CREATE INDEX PersonIndex ON Person (LastName DESC) ",
  "insert into tablename (name,age) values('aaa',12)",
  "UPDATE Person SET FirstName = 'Fred' WHERE LastName = \"Wilson\" ",
  "delete from abc where id = 123",
  "select * from abc;delete from abc where id =12",
  //"ALTER TABLE Persons ADD Birthday date",
  //"DROP INDEX table_name.index_name",
  //"ALTER TABLE xxx RENAME TO yyy",
  "select 1 ",
 " SELECT s.*, v.userId   AS 'visitoruser.userId', v.tenantId AS 'visitoruser.tenantId', v.nicename AS 'visitoruser.nicename' FROM servicesession s JOIN visitoruser v ON s.visitoruserid = v.userid WHERE (s.state = 'Processing' OR s.state = 'Resolved') AND s.tenantId = 123  AND s.agentUserId = 1232  order by s.createDatetime "
];
node_lemon.parse(sqls.join(';'),function(err,rs){
  rs.statements.forEach(function(state,index){
    console.log(index,state.type);
  });
});
