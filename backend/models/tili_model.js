const db = require('../database');

const tili = {
  getAll: function(callback) {
    return db.query('select * from tili', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from tili where idTili=?', [id], callback);
  },
  add: function(tili, callback) {
    return db.query(
      'insert into tili (Debittilinumero,Credittilinumero,DebitSaldo,CreditSaldo,Luottoraja) values(?,?,?,?,?)',
      [tili.Debittilinumero, tili.Credittilinumero, tili.DebitSaldo, tili.CreditSaldo, tili.Luottoraja],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tili where idTili=?', [id], callback);
  },
  update: function(id, tili, callback) {
    return db.query(
      'update tili set Debittilinumero=?,Credittilinumero=?,DebitSaldo=?, CreditSaldo=?,Luottoraja=? where idTili=?',
      [tili.Debittilinumero, tili.Credittilinumero,tili.DebitSaldo, tili.CreditSaldo, tili.Luottoraja, id],
      callback
    );
  }
};
module.exports = tili;