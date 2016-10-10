var addon = require('./build/Release/lemon.node');
var types = require('./src/type');
module.exports = {
  parse:function(sql,cb){
    addon.parse(sql,function(err,rs){
      rs.statements.forEach(function(item,index){
        item.type = types[item.type];
      });
      cb(err,rs);
    });
  }
};
