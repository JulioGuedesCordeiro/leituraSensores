import { Router } from 'express';
import Luz from './src/modulos/sensores/luz/luz.controller';
import Temperatura from './src/modulos/sensores/temperatura/temperatura.controller';
import Umidade from './src/modulos/sensores/umidade/umidade.controller';

const api = Router();

api.use('/api/luz', Luz);
api.use('/api/temperatura', Temperatura);
api.use('/api/umidade', Umidade);

export default api;
