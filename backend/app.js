var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const dotenv=require('dotenv');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var asiakasRouter = require('./routes/asiakas');  
var korttiRouter = require('./routes/kortti');
var tiliRouter = require('./routes/tili');
var nostoRouter = require('./routes/nosto');
var nostoHRouter = require('./routes/nostoH');
var loginRouter = require('./routes/login');
var asiakasTiliRouter = require('./routes/asiakasTili');
var debitSaldoRouter = require('./routes/debitSaldo');
var creditSaldoRouter = require('./routes/creditSaldo');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/login', loginRouter);
app.use('/kortti', korttiRouter);
app.use(authenticateToken);
app.use('/tili', tiliRouter);
app.use('/users', usersRouter);
app.use('/asiakas', asiakasRouter);
app.use('/nosto', nostoRouter);
app.use('/nostoH', nostoHRouter);
app.use('/asiakasTili', asiakasTiliRouter);
app.use('/debitSaldo', debitSaldoRouter);
app.use('/creditSaldo', creditSaldoRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

module.exports = app;
