const express = require('express');
const router = express.Router();
const debitSaldo = require('../models/debitSaldo_model');

router.put('/:id', 
function(request, response) {
 debitSaldo.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;