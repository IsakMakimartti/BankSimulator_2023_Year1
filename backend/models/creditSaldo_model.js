const db = require('../database');

const creditSaldo = {
  update: function(id, creditSaldo, callback) {
    return db.query(
      'update tili set CreditSaldo=? where idTili=?',
      [creditSaldo.CreditSaldo, id],
      callback
    );
  }
};
module.exports = creditSaldo;