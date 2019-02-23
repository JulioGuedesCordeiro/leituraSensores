import express from 'express';
import bodyParser from 'body-parser';
import api from './routes';

const app = express();
const PORT = process.env.PORT || 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(api);

app.listen(PORT, () => {
  console.log(`Escutando na porta ${PORT}.`);
});

module.exports = app;
