const express = require('express');
const router = express.Router();
const nostoH = require('../models/nostoH_model');

router.get('/:id/:id2/:id3',
    function (request, response) {
     nostoH.getById(request.params.id, request.params.id2, request.params.id3, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });

module.exports = router;