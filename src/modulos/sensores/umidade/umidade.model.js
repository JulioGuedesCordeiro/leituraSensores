import { bookshelf } from '../../../../bookshelf';

const SensorUmidade = bookshelf.Model.extend({
  tableName: 'sensor_umidade',
  idAttribute: 'sensor_umidade_id',
  hasTimestamps: ['criado_em', 'atualizado_em'],
}, {
    listar(page = 0, pageSize = 10, pesquisa = '') {
      const query = this
        .query((umi) => {
          umi.where('umidade', 'LIKE', `%${pesquisa}%`);
        });
      if (page) {
        return query.fetchPage({ page, pageSize });
      }
      return query.fetchAll();
    },
    salvar(umidade) {
      this.forge({umidade}).save();
    }
  });

export default SensorUmidade;