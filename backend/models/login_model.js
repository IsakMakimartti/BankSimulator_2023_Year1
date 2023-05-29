const db = require('../database');

const login={
 checkPassword:function(login_idKortti, callback){
    return db.query ('select pinkoodi from kortti where idKortti=?', login_idKortti,callback);
 }
}

module.exports=login;