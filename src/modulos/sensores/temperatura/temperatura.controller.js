import { Router } from 'express';
import model from './temperatura.model';

const api = Router();

api.get('/', async (req, res, next) => {
  try {
    const { page, size, pesquisa } = req.query;
    const temperatura = await model.listar(page, size, pesquisa);
    if (temperatura.lenght === 0) {
      return res.status(404).json({ message: 'Recurso não encontrado.' });
    }
    const { models, pagination } = temperatura;
    return res.status(200).json({ data: models, meta: pagination });
  } catch (erro) {
    return next(erro);
  }
});

api.post('/:temperatura', async (request, response, next) => {
  try {
    const resposta = await model.salvar(request.params.temperatura);
    return response.status(200).send({ message: 'Gravado com Sucesso', resposta });
  } catch (erro) {
    return next(erro);
  }
});


export default api;