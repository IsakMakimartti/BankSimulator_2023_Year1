const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.idKortti && request.body.pinkoodi){
      const user = request.body.idKortti;
      const pass = request.body.pinkoodi;
        login.checkPassword(user, function(err, dbResult) {
          if(err){
            console.log("dbError");
            response.json(err);
          }

          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pass, dbResult[0].pinkoodi, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  const token = generateAccessToken({ username: user });
                  response.send(token);
                  console.log(token);
                } else {
                    console.log("False");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("username or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;