import { bookshelf } from '../../../../bookshelf';

const SensorTemperatura = bookshelf.Model.extend({
  tableName: 'sensor_temperatura',
  idAttribute: 'sensor_temperatura_id',
  hasTimestamps: ['criado_em', 'atualizado_em'],
}, {
    listar(page = 0, pageSize = 10, pesquisa = '') {
      const query = this
        .query((temp) => {
          temp.where('temperatura', 'LIKE', `%${pesquisa}%`);
        });
      if (page) {
        return query.fetchPage({ page, pageSize });
      }
      return query.fetchAll();
    },
    salvar(temperatura) {
      this.forge({temperatura}).save();
    }
  });

export default SensorTemperatura;