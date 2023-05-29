const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds = 10; 

const kortti = {
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from kortti where idKortti=?', [id], callback);
  },
  add: function(kortti, callback) {
      bcrypt.hash(kortti.pinkoodi, saltRounds, function (err, hashed_password){
        console.log(kortti.pinkoodi);
        console.log(hashed_password);
      return db.query('insert into kortti (Pinkoodi,idAsiakas,idTili) values(?,?,?)',
      [hashed_password, kortti.idAsiakas, kortti.idTili],
      callback);
      });
  },
  delete: function(id, callback) {
    return db.query('delete from kortti where idKortti=?', [id], callback);
  },
  update: function(id, kortti, callback) {
    bcrypt.hash(kortti.pinkoodi, saltRounds, function (err, hashed_password){
      return db.query('update kortti set Pinkoodi=?,idAsiakas=?, idTili=? where idKortti=?',
      [hashed_password, kortti.idAsiakas, kortti.idTili, id],
      callback);
    });
  }
};
module.exports = kortti;