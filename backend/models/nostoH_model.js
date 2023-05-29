const db = require('../database');

const nostoH = {
    getById: function(id, id2, id3, callback) {
        const offset = parseInt(id3);
      return db.query('select * from nostohistoria where debit=? and idTili=? order by datetime desc limit 5 offset ?', [id, id2, offset], callback);
    },
  };
  module.exports = nostoH;