namespace bitsmithery
{
	namespace core
	{
		inline entity_id_generator::entity_id_generator()
			: next_id(entity_id_invalid + 1)
		{}

		inline entity_id entity_id_generator::operator()()
		{
			return next_id.fetch_add(1);
		}
	}
}
