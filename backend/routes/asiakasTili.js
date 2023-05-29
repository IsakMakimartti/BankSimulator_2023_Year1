const express = require('express');
const router = express.Router();
const pankki = require('../models/asiakasTili_model');

router.get('/',
    function (request, response) {
     pankki.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/:id',
    function (request, response) {
     pankki.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });
    
router.get('/:id/:id2',
    function (request, response) {
     pankki.getById2(request.params.id, request.params.id2, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });

router.post('/', 
function(request, response) {
 pankki.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});

module.exports = router;