const db = require('../database');

const asiakasTili = {
  getAll: function(callback) {
    return db.query('select * from asiakas_tili', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from asiakas_tili where idAsiakas=?', [id], callback);
  },
  getById2: function(id, id2, callback) {
    return db.query('select * from asiakas_tili where idAsiakas=? and idTili =?', [id, id2], callback);
  },
  add: function(asiakas_Tili, callback) {
    return db.query(
      'insert into asiakas_tili (idAsiakas, idTili, Omistaja, PaivaNostoraja) values(?,?,?,?)',
      [asiakas_Tili.idAsiakas, asiakas_Tili.idTili, asiakas_Tili.Omistaja, asiakas_Tili.PaivaNostoraja],
      callback
    );
  }
};
module.exports = asiakasTili;