const express = require('express');
const router = express.Router();
const creditSaldo = require('../models/creditSaldo_model');

router.put('/:id', 
function(request, response) {
 creditSaldo.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;