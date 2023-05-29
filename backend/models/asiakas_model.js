const db = require('../database');

const asiakas = {
  getAll: function(callback) {
    return db.query('select * from asiakas', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from asiakas where idAsiakas=?', [id], callback);
  },
  add: function(asiakas, callback) {
    return db.query(
      'insert into asiakas (etunimi,sukunimi,Osoite) values(?,?,?)',
      [asiakas.etunimi, asiakas.sukunimi, asiakas.Osoite],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from asiakas where idAsiakas=?', [id], callback);
  },
  update: function(id, asiakas, callback) {
    return db.query(
      'update asiakas set etunimi=?,sukunimi=?, Osoite=? where idAsiakas=?',
      [asiakas.etunimi, asiakas.sukunimi, asiakas.Osoite, id],
      callback
    );
  }
};
module.exports = asiakas;