const db = require('../database');

const debitSaldo = { 
  update: function(id, debitSaldo, callback) {
    return db.query(
      'update tili set DebitSaldo=? where idTili=?',
      [debitSaldo.DebitSaldo, id],
      callback
    );
  }
};
module.exports = debitSaldo;