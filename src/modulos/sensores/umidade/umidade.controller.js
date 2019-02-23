import { Router } from 'express';
import model from './umidade.model';

const api = Router();

api.get('/', async (req, res, next) => {
  try {
    const { page, size, pesquisa } = req.query;
    const umidade = await model.listar(page, size, pesquisa);
    if (umidade.lenght === 0) {
      return res.status(404).json({ message: 'Recurso não encontrado.' });
    }
    const { models, pagination } = umidade;
    return res.status(200).json({ data: models, meta: pagination });
  } catch (erro) {
    return next(erro);
  }
});

api.post('/:umidade', async (request, response, next) => {
  try {
    const resposta = await model.salvar(request.params.umidade);
    return response.status(200).send({ message: 'Gravado com Sucesso', resposta });
  } catch (erro) {
    return next(erro);
  }
});


export default api;