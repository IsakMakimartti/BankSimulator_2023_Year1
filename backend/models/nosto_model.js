const db = require('../database');

const nosto = {
  getAll: function(callback) {
    return db.query('select * from nostohistoria', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from nostohistoria where idNostoHistoria=?', [id], callback);
  },
  add: function(nostohistoria, callback) {
    return db.query(
      'insert into nostohistoria (DATETIME,MAARA,Debit,idTili) values(?,?,?,?)',
      [nostohistoria.DATETIME, nostohistoria.MAARA, nostohistoria.Debit, nostohistoria.idTili],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from nostohistoria where idNostoHistoria=?', [id], callback);
  },
  update: function(id, nostohistoria, callback) {
    return db.query(
      'update nostohistoria set DATETIME=?,MAARA=?, Debit=?, idTili=? where idNostoHistoria=?',
      [nostohistoria.DATETIME, nostohistoria.MAARA, nostohistoria.Debit, nostohistoria.idTili, id],
      callback
    );
  }
};
module.exports = nosto;